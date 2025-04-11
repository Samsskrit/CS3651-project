import pretty_midi
import random

def __main__():
    midi_data = pretty_midi.PrettyMIDI('midi/riptide.mid')

    notes = set()
    print(midi_data.instruments)
    for instrument in midi_data.instruments:
        if instrument.name == "Flute":
            for note in instrument.notes:
                notes.add(note.start)

    notes = sorted(list(notes), key=lambda x: x)

    note_data = [(note, True, random.randint(0, 3)) for note in notes]

    for note in note_data:
        if note[1]:
            note_data.append((note[0] + 2, False, -1))

    note_data = sorted(note_data, key=lambda x: x[0])

    with open('output/rhythm_data_new.txt', 'w') as output_file:
        output_file.write("struct rhythm_data {\n");
        output_file.write("    double note_start;\n");
        output_file.write("    bool is_note;\n");
        output_file.write("    int led_channel;\n");
        output_file.write("};\n\n");
        output_file.write("struct rhythm_data rhythm_data[] = {\n");
        for note in note_data:
            output_file.write(f"    {{ {note[0]:.3f}, {str(note[1]).lower()}, {note[2]} }},\n")
        output_file.write("};\n")

    print("Rhythm data has been saved to 'output/rhythm_data.txt'.")


if __name__ == "__main__":
    __main__()