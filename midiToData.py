import pretty_midi

# Load MIDI file
midi_data = pretty_midi.PrettyMIDI('midi/riptide.mid')

notes = set()
for instrument in midi_data.instruments:
    if not instrument.is_drum:
        for note in instrument.notes:
            notes.add((note.start, note.end))

notes = sorted(list(notes), key=lambda x: x[0])

with open('output/rhythm_data.txt', 'w') as output_file:
    for start, end in notes:
        output_file.write(f"{start:.3f},{end:.3f}\n")

print("Rhythm data has been saved to 'output/rhythm_data.txt'.")