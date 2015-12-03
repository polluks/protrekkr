<pre>
Compiling the tracker on an already supported operating system will require<br>
the 3 src/extralibs (that is SDL_draw, tinyxml & zlib-1.2.3) to be generated first,<br>
only the tracker itself can be generated with either one of the makefiles<br>
of the top directory or via the visual studio project.<br>
<br>
In order to use the replay routine either use the provided makefiles or vc studio<br>
projects located in the release/distrib/replay directory, a .ptp module file<br>
and a ptk_properties.h source file both generated by the tracker.<br>
Replace the PTK_MODULE variable content of the assembly files located<br>
in release/distrib/replay/test with the filename of the .ptp module and compile.<br>
<br>
== Porting ==<br>
<br>
In order to port the tracker to another operating system, several<br>
issues should be considered (beside crafting the relevant makefiles, that is):<br>
<br>
1. The keyboard handling :<br>
<br>
It is important for the keyboard to behave identically on every port.<br>
The input is usually handled differently depending on the computer or even the<br>
operating system, for example the Windows version doesn't require keyboard<br>
definition files but the Linux one does and on Mac OS X the translation<br>
to unicode is handled differently.<br>
<br>
2. The executable path :<br>
<br>
The variable "ExePath" must be filled with the current path of the executable<br>
file during main(), all the data loading are relative to this variable.<br>
<br>
The way to obtain it can be different depending on the operating system.<br>
<br>
3. The midi drivers :<br>
<br>
These can be disabled at compilation by using the __NOMIDI__ constant,<br>
the midi in/out drivers are located in src/midi/midi_drv_xxxxx.cpp files.<br>
<br>
The functions of the drivers mainly concern enumerating the devices, opening<br>
them, receiving/sending messages and calling the callback function for incoming<br>
messages.<br>
<br>
4. The codecs :<br>
<br>
To reduce the size of the modules, the tracker is using (lossy) codecs present<br>
in the operating system to pack (and depack) the samples in .ptp module files.<br>
This can be disabled at compilation too by using the __NOCODEC__ constant.<br>
I'll try to come up with an acceptable solution for operating systems which do not<br>
come with codecs pre-installed.<br>
<br>
Note that packing samples in .ptp files is not mandatory<br>
(the packing scheme for each sample can be set to none in the tracker).<br>
</pre>