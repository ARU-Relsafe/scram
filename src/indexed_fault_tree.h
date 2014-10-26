#ifndef SCRAM_SRC_INDEXED_FAULT_TREE_H_
#define SCRAM_SRC_INDEXED_FAULT_TREE_H_

#include <set>
#include <string>

#include <boost/unordered_map.hpp>

#include "event.h"
#include "indexed_gate.h"

typedef boost::shared_ptr<scram::Gate> GatePtr;

namespace scram {

/// @class IndexedFaultTree
/// This class should provide simpler representation of a fault tree
/// that takes into account the indexes of events instead of ids and pointers.
class IndexedFaultTree {
  // This class should:
  // 1. Use indices of events.
  // 2. Propagate fault tree constants (House events).
  // 3. Unroll complex gates like XOR and VOTE.
  // 4. Pre-process the tree to simplify the structure.
  // 5. Take into account non-coherent logic for the fault tree.
  // Ideally, the resulting tree should have only OR and AND gates with
  // basic event and gate indices only.
  // The indices of gates may change, but the indices of basic events must
  // not change.
 public:
  /// Constructs a simplified fault tree.
  /// @param[in] top_event_id The index of the top event of this tree.
  IndexedFaultTree(int top_event_id);

  /// Removes all newly allocated gates to describe the simplified tree.
  ~IndexedFaultTree();

  /// Creates indexed gates with basic and house event indices as children.
  /// This function also simplifies the tree to simple gates.
  /// @param[in] int_to_inter Container of gates and thier indices including
  ///                         the top gate.
  /// @param[in] all_to_int Container of all events in this tree to index
  ///                       children of the gates.
  void InitiateIndexedFaultTree(
      const boost::unordered_map<int, GatePtr>& int_to_inter,
      const boost::unordered_map<std::string, int>& all_to_int);

  /// Remove all house events by propagating them as constants in Boolean
  /// equation.
  /// @param[in] true_house_events House events with true state.
  /// @param[in] false_house_events House events with false state.
  void PropagateConstants(const std::set<int>& true_house_events,
                          const std::set<int>& false_house_events);

  /// Performs processing of a fault tree.
  void ProcessIndexedFaultTree();

  inline const std::set<int>& GateChildren(int index) {
    return indexed_gates_.find(index)->second->children();
  }

  /// @todo Return numbers instead.
  inline std::string GateType(int index) {
    return indexed_gates_.find(index)->second->string_type();
  }

  /// @returns the state of a gate.
  inline std::string GateState(int index) {
    return indexed_gates_.find(index)->second->state();
  }

  inline int top_event_sign() {
    assert(top_event_sign_ == 1 || top_event_sign_ == -1);
    return top_event_sign_;
  }

 private:
  /// Start unrolling gates to simplify gates to OR and AND gates.
  void StartUnrollingGates();

  /// Unrolls the top gate.
  /// @param[out] top_gate The top gate to start unrolling with.
  void UnrollTopGate(IndexedGate* top_gate);

  /// Unrolls a gate.
  /// @param[in] gate_index The index of the current gate.
  /// @param[out] parent_gate The current parent of the gate to process.
  void UnrollGate(int gate_index, IndexedGate* parent_gate);

  /// Unrolls a gate with XOR logic.
  /// @param[out] gate The gate to unroll.
  void UnrollXorGate(IndexedGate* gate);

  /// Unrolls a gate with "atleast" gate and vote number.
  /// @param[out] gate The atleast gate to unroll.
  void UnrollAtleastGate(IndexedGate* gate);

  /// Remove all house events from a given gate.
  /// @param[in] true_house_events House events with true state.
  /// @param[in] false_house_events House events with false state.
  /// @param[out] gate The final resultant processed gate.
  void PropagateConstants(const std::set<int>& true_house_events,
                          const std::set<int>& false_house_events,
                          IndexedGate* gate);

  /// This method pre-processes the tree by doing Boolean algebra.
  /// At this point all gates are expected to be either OR type or AND type.
  /// Preprocesses the fault tree.
  /// Merges similar gates.
  /// @param[in] gate The starting gate to traverse the tree. This is for
  ///                 recursive purposes.
  void PreprocessTree(IndexedGate* gate);

  /// Process null gates.
  void ProcessNullGates(IndexedGate* parent);

  int top_event_index_;  ///< The index of the top gate of this tree.
  /// All gates of this tree including newly created ones.
  boost::unordered_map<int, IndexedGate*> indexed_gates_;
  /// To keep track for already unrolled gates.
  std::set<int> unrolled_gates_;
  /// To keep track for already pre-processed gates.
  std::set<int> preprocessed_gates_;
  /// To keep track for NULL pre-processed gates.
  std::set<int> null_gates_;
  int top_event_sign_;  ///< The negative or positive sign of the top event.
  int new_gate_index_;  ///< Index for a new gate.
};

}  // namespace scram

#endif  // SCRAM_SRC_INDEXED_FAULT_TREE_H_
