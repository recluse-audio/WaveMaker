/*
  ==============================================================================

    AudioBufferWriter.h
    Created: 18 Jan 2022 5:28:05am
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/*
    Write from a buffer to a given file path
*/
class BufferWriter
{
public:
    BufferWriter()
    {
        formatManager.registerBasicFormats();
    }
    ~BufferWriter(){}

    void writeBufferToDisk(AudioBuffer<float>& buffer, StringRef filePath, StringRef fileName)
    {
        AudioBuffer<float> longBuff;
        longBuff.setSize(1, buffer.getNumSamples() * 40);
        longBuff.clear();

        auto* buffRead = buffer.getArrayOfReadPointers();
        auto* buffWrite = longBuff.getArrayOfWritePointers();

        for (int i = 0; i < buffer.getNumSamples() * 40; i++)
        {
            
            int modulo = i % buffer.getNumSamples() - 1;
       
            buffWrite[0][i] = buffRead[0][modulo]; 
        }

        File file(filePath);
        File newFile = file.getNonexistentChildFile(fileName, ".wav");
       // file.deleteFile();

       //**** this section is inspired by a dan foley thing that I can't find the link to of course
        //  notice how release() is called as the output stream is created
        auto* outputStream = newFile.createOutputStream().release();
        WavAudioFormat format;

        std::unique_ptr <AudioFormatWriter> writer;
        writer.reset(format.createWriterFor(outputStream, 48000.0, 1, 24, {}, 0));
    
        if (writer.get() != nullptr)
        {
            writer->writeFromAudioSampleBuffer(longBuff, 0, longBuff.getNumSamples());

        }
        else
        {
            delete outputStream;
        }

        //**** end foley section
    }

private:
    AudioFormatManager formatManager;
};