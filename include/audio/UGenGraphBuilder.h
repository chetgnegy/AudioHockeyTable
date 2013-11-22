/*
  Author: Chet Gnegy
  chetgnegy@gmail.com

  UGenGraphBuilder.h
  This class uses the positions of the discs and 
  the ugens to build a signal flow graph
*/


#ifndef _UGENGRAPHBUILDER_H_
#define _UGENGRAPHBUILDER_H_

#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include "UnitGenerator.h"
#include "Disc.h"
#include "Thread.h"

class GraphData;


typedef std::pair<Disc *, double > Edge; 
typedef std::pair<Disc *, Disc * > Wire; 


class UGenGraphBuilder {
public:

  static const double kMaxDist = 7.0;
  UGenGraphBuilder(int buffer_length);
  ~UGenGraphBuilder();

  // Recomputes the graph based on the new positions of the discs
  void rebuild();

  // Processes a single sample. Note that you must first handoff audio 
  // and midi data to the graph by using the handoff_audio and 
  // handoff midi functions
  double tick();
  void load_buffer(double *out, int length); // a whole buffer

  // Prints all data about the graph, including the nodes,
  // their type and positions
  void print_all();

  // Passes any audio samples to the Input ugens. 
  void handoff_audio(double samples);
  void handoff_audio_buffer(double *buffer, int samples);

  // Passes any midi notes the MidiUnitGenerators. Decides using the
  // value of velocity whether the event is a note on or a note off
  void handoff_midi(int MIDI_pitch, int velocity);

  // Adds a unit generator to the signal chain. Returns false for invalid
  // ugen type
  bool add_effect(Disc *fx);
  
  // Adds midi unit generator to a list of objects that must be checked
  // when new midi event is created. Returns false for invalid
  // ugen type
  bool add_input(Disc *input);

  // Adds midi unit generator to a list of objects that must be checked
  // when new midi event is created. Returns false for invalid
  // ugen type
  bool add_midi_ugen(Disc *mugen);

  // Removes a disc from the graph and deletes the disc
  bool remove_disc(Disc *ugen);

  void lock_thread(bool lock);

  // Lets the other thread know that the FFT is ready to compute
  void signal_fft();
  bool fft_signaled(){return fft_ready_;}

  // The graphics thread can grab this and display it
  void calculate_fft();

  complex *get_fft();
  int get_fft_length(){return buffer_length_/2;}
  

  std::vector<Wire> wires_;

  std::vector<Disc *> sinks_;
private:
  // The distance between two discs
  double get_edge_cost(Disc* a, Disc* b);

  void find_edges();

  // Reverses the push architecture of "out = tick(in)" to recursively pull
  // samples to the output sinks from the inputs
  double pull_result(UnitGenerator *k, std::vector<Disc *> inputs);
  double *pull_result_buffer(UnitGenerator *k, std::vector<Disc *> inputs, int length);

  void switch_wire_direction(Wire &w);

  

  // Allows all ugens to be called uniformly
  Disc *indexed(int i);

  // The chain of effects that is processed before being sent to the output
  std::vector<Disc *> fx_;
  
  // The list of audio inputs that receive samples
  std::vector<Disc *> inputs_;
  
  // The list of unit generators that require midi events to work
  std::vector<Disc *> midi_modules_;
  
  
  std::map < Disc *, GraphData > data_;

  Mutex audio_lock_;

  int buffer_length_;

  complex *fft_;
  bool fft_ready_;
};


class GraphData{
public:
  GraphData();
  ~GraphData();
  void list_edges();
  std::vector< Edge > edges_;
  std::vector< Disc* > inputs_;
  std::vector< Disc* > outputs_;
  
};


#endif
