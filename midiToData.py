import pretty_midi

def __main__():
    midi_data = pretty_midi.PrettyMIDI('midi/riptide.mid')

    notes = set()
    print(midi_data.instruments)
    for instrument in midi_data.instruments:
        if instrument.name == "Flute":
            for note in instrument.notes:
                notes.add(note.start)

    notes = sorted(list(notes), key=lambda x: x)
    # deleteOverlap(notes)

    with open('output/rhythm_data.txt', 'w') as output_file:
        for start in notes:
            output_file.write(f"{start:.3f},\n")

    print("Rhythm data has been saved to 'output/rhythm_data.txt'.")

def deleteOverlap(notes):
    # notes = sorted(notes, key=lambda x: x[0])
    non_overlapping_notes = []
    for note in notes:
        if not non_overlapping_notes or note[0] >= non_overlapping_notes[-1][1]:
            non_overlapping_notes.append(note)

    with open('output/overlap_debug.txt', 'w') as debug_file:
        for note in non_overlapping_notes:
            debug_file.write(f"{note}\n")
    return non_overlapping_notes

if __name__ == "__main__":
    __main__()