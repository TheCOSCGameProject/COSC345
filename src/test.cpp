#include "../lib/combat.h"
// #include "../helper/minigames.cpp"
#include "../lib/player.h"
#include "../lib/toolkit.h"
#include "../lib/room.h"
#include "../lib/dungeon.h"
#include "../lib/menu.h"
#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioToolbox.h>
#include <iostream>

void playSound(const char *path)
{
    // Create an AudioFileID
    AudioFileID audioFileID;
    AudioFileOpenURL(CFURLCreateWithFileSystemPath(kCFAllocatorDefault, CFStringCreateWithCString(kCFAllocatorDefault, path, kCFStringEncodingUTF8), kCFURLPOSIXPathStyle, false), kAudioFileReadPermission, kAudioFileWAVEType, &audioFileID);

    // Prepare for playback
    AudioStreamBasicDescription streamFormat;
    UInt32 size = sizeof(streamFormat);
    AudioFileGetProperty(audioFileID, kAudioFilePropertyDataFormat, &size, &streamFormat);

    // Create a new AudioQueue for playback
    AudioQueueRef queue;
    AudioQueueNewOutput(&streamFormat, nullptr, nullptr, nullptr, nullptr, 0, &queue);

    // Enqueue audio data (this is just a placeholder for actual implementation)
    // In a real implementation, you would need to read data from the file and enqueue it

    // Start playback
    AudioQueueStart(queue, nullptr);

    // Clean up
    AudioFileClose(audioFileID);
    AudioQueueDispose(queue, true);
}

int main()
{

    // combatV1(1000, 10, 3000, "JEff");
    // clear(5);
    // combatV1(1000, 10, 3000, "JEfecdwwedf");

    // BlackJack bj;
    // bj.start();

    Player p;
    p.removeFromInventory("arrow");
    playSound("oof.wav");

    return 0;
}