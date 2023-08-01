using AudioSwitcher.AudioApi.CoreAudio;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volume_Mixer
{
    internal class VolumeMixer
    {
        CoreAudioDevice defaultPlaybackDevice;
        CoreAudioDevice defaultInputDevice;

        

        static void Main(string[] args)
        {
            SerialPort port = new SerialPort();
            VolumeMixer volumeMixer = new VolumeMixer();

            port.BaudRate = 9600;
            port.PortName = "COM3";


            volumeMixer.setCoreAudioDevices();


        }

        void setCoreAudioDevices()
        {
            defaultPlaybackDevice = new CoreAudioController().DefaultPlaybackDevice;
            defaultInputDevice = new CoreAudioController().DefaultCaptureDevice;
            Console.WriteLine($"{defaultPlaybackDevice.FullName} + {defaultInputDevice.FullName}");
        }


    }
}
