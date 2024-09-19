#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CoreFoundation.h>
#include <iostream>

// Global variables to manage audio file and reading position
AudioFileID audioFileID;
SInt64 filePosition = 0; // Current read position in the file

void audioQueueOutputCallback(void *inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer)
{
    // Read audio data from the file into the buffer
    UInt32 numBytesRead = 0;
    OSStatus status = AudioFileReadBytes(audioFileID, false, filePosition, &numBytesRead, inBuffer->mAudioData);

    if (status != noErr)
    {
        std::cerr << "Error reading audio data: " << status << std::endl;
        // Stop playback if reading fails
        AudioQueueStop(inAQ, true);
        return;
    }

    inBuffer->mAudioDataByteSize = numBytesRead;

    // If end of file is reached, stop the queue
    if (numBytesRead == 0)
    {
        AudioQueueStop(inAQ, true);
        return;
    }

    // Update the file position
    filePosition += numBytesRead;

    // Enqueue the buffer for playback
    status = AudioQueueEnqueueBuffer(inAQ, inBuffer, 0, nullptr);
    if (status != noErr)
    {
        std::cerr << "Error enqueueing audio buffer: " << status << std::endl;
    }
}

void playSound(const char *path)
{
    // Create an AudioFileID
    CFURLRef fileURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, CFStringCreateWithCString(kCFAllocatorDefault, path, kCFStringEncodingUTF8), kCFURLPOSIXPathStyle, false);
    OSStatus status = AudioFileOpenURL(fileURL, kAudioFileReadPermission, kAudioFileWAVEType, &audioFileID);

    if (status != noErr)
    {
        std::cerr << "Error opening audio file: " << status << std::endl;
        CFRelease(fileURL);
        return;
    }

    // Prepare for playback
    AudioStreamBasicDescription streamFormat;
    UInt32 size = sizeof(streamFormat);
    status = AudioFileGetProperty(audioFileID, kAudioFilePropertyDataFormat, &size, &streamFormat);

    if (status != noErr)
    {
        std::cerr << "Error getting audio file property: " << status << std::endl;
        AudioFileClose(audioFileID);
        CFRelease(fileURL);
        return;
    }

    // Create a new AudioQueue for playback
    AudioQueueRef queue;
    status = AudioQueueNewOutput(&streamFormat, audioQueueOutputCallback, nullptr, nullptr, nullptr, 0, &queue);

    if (status != noErr)
    {
        std::cerr << "Error creating audio queue: " << status << std::endl;
        AudioFileClose(audioFileID);
        CFRelease(fileURL);
        return;
    }

    // Allocate and enqueue buffers
    const int numBuffers = 3;
    AudioQueueBufferRef buffers[numBuffers];
    for (int i = 0; i < numBuffers; ++i)
    {
        status = AudioQueueAllocateBuffer(queue, 4096, &buffers[i]);
        if (status != noErr)
        {
            std::cerr << "Error allocating audio buffer: " << status << std::endl;
            AudioQueueDispose(queue, true);
            AudioFileClose(audioFileID);
            CFRelease(fileURL);
            return;
        }

        // Enqueue the buffer initially
        status = AudioQueueEnqueueBuffer(queue, buffers[i], 0, nullptr);
        if (status != noErr)
        {
            std::cerr << "Error enqueueing audio buffer: " << status << std::endl;
            AudioQueueDispose(queue, true);
            AudioFileClose(audioFileID);
            CFRelease(fileURL);
            return;
        }
    }

    // Start playback
    status = AudioQueueStart(queue, nullptr);
    if (status != noErr)
    {
        std::cerr << "Error starting audio queue: " << status << std::endl;
    }
    else
    {
        std::cout << "Playback started." << std::endl;
    }

    // Clean up
    AudioQueueDispose(queue, true);
    AudioFileClose(audioFileID);
    CFRelease(fileURL);
}

int main()
{
    playSound("oof.wav");
    return 0;
}
