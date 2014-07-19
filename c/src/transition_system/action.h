#ifndef TRANSITION_SYSTEM_ACTION_H_
#define TRANSITION_SYSTEM_ACTION_H_

#include <map>
#include <string>
#include <vector>
#include <memory>

class Word;
/*! @class Action
 *  @brief class representing action
*/
class Action {
 public:
  Action(const std::string& name, const EntitySet& creator, const EntitySet& eraser, const EntitySet& reader, const EntitySet& embargoes)
    : name_(name), creator_(creator), reader_(reader), eraser_(eraser), embargoes_(embargoes) {}

  // void AddSimulate(const Action* action) { simulates_.insert(std::make_pair(action->name(), true)); }
  // void AddDisable(const Action* action) { disables_.insert(std::make_pair(action->name(), true)); }

  // bool Simulates(const Action* action) const { return simulates_.find(action->name()) != simulates_.end(); }
  // bool Disables(const Action* action) const { return disables_.find(action->name()) != disables_.end(); }

  bool Simulates(const Action* action) const {
    EntitySet tmp, condition;
    std::set_union(action->reader().begin(), action->reader().end(), action->eraser().begin(), action->eraser().end(), back_inserter(tmp));
    std::set_intersection(creator_.begin(), creator_.end(), tmp.begin(), tmp.end(), back_inserter(condition));
    if (!condition.empty()) return true;

    tmp.clear();
    condition.clear();
    std::set_union(action->creator().begin(), action->creator().end(), action->embargoes().begin(), action->embargoes().end(), back_inserter(tmp));
    std::set_intersection(eraser_.begin(), eraser_.end(), tmp.begin(), tmp.end(), back_inserter(condition));

    return !condition.empty();
  }

  bool Disables(const Action* action) const {
    EntitySet tmp, condition;
    std::set_union(action->reader().begin(), action->reader().end(), action->eraser().begin(), action->eraser().end(), back_inserter(tmp));
    std::set_intersection(eraser_.begin(), eraser_.end(), tmp.begin(), tmp.end(), back_inserter(condition));
    if (!condition.empty()) return true;

    tmp.clear();
    condition.clear();
    std::set_union(action->creator().begin(), action->creator().end(), action->embargoes().begin(), action->embargoes().end(), back_inserter(tmp));
    std::set_intersection(creator_.begin(), creator_.end(), tmp.begin(), tmp.end(), back_inserter(condition));

    return !condition.empty();
  }

  bool Influences(const Action* action) const { return Simulates(action) || action->Disables(this); }

  std::unique_ptr<Word> CalcPrimeCause(const Word& word) const;

  bool Equals(const Action* other) const { return name_ == other->name(); }

  const std::string& name() const { return name_; }
  const EntitySet& creator() const { return creator_; }
  const EntitySet& reader() const { return reader_; }
  const EntitySet& eraser() const { return eraser_; }
  const EntitySet& embargoes() const { return embargoes_; }

 private:
  const std::string name_;
  const EntitySet creator_;
  const EntitySet reader_;
  const EntitySet eraser_;
  const EntitySet embargoes_;

  // std::map<std::string, bool> simulates_;
  // std::map<std::string, bool> disables_;

  DISALLOW_COPY_AND_ASSIGN(Action);
};

#endif  // TRANSITION_SYSTEM_ACTION_H_
