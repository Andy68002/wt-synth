#!/usr/bin/env python3
#
# test_midiin_poll.py
#
"""Show how to receive MIDI input by polling an input port."""

from __future__ import print_function
#from subprocess import Popen, PIPE
import traceback

import logging
import os
import sys
import time
import io
import signal
from rtmidi.midiutil import open_midiinput
from mido import MidiFile

#signal.signal(signal.SIGPIPE, signal.SIG_DFL)


#mid = MidiFile('song.mid')
#for i, track in enumerate(mid.tracks):
#    print('Track {}: {}'.format(i, track.name))
#    for msg in track:
#        print(msg)



log = logging.getLogger('midiin_poll')
logging.basicConfig(level=logging.DEBUG)

# Prompts user for MIDI input port, unless a valid port number or name
# is given as the first argument on the command line.
# API backend defaults to ALSA on Linux.
port = sys.argv[1] if len(sys.argv) > 1 else None

try:
    midiin, port_name = open_midiinput(port)
except (EOFError, KeyboardInterrupt):
    sys.exit()

print("Entering main loop of python")

try:
    timer = time.time()
    player_piano_flag = 0
    while True:
            msg = midiin.get_message()
            if msg:
                message, deltatime = msg
                timer += deltatime
                print(str(message))
                if(message[1] == 105):
                    #player_piano_flag = 1
                    #print("made it")
                    for msg in MidiFile('song.mid'):
                        time.sleep(msg.time)
                        if not msg.is_meta:
                            if(msg.type == 'note_on'):
                                print ('[144,', msg.note, ',', msg.velocity, ']')
                            elif (msg.type == 'note_off'):
                                print ('[128,', msg.note, ',', msg.velocity, ']')
                sys.stdout.flush()
            time.sleep(0.01)
except KeyboardInterrupt:
    sys.stderr.write('')
finally:
    sys.stderr.write("Exit.\n")
    midiin.close_port()
    del midiin
