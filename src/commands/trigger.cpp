#include "commands/trigger.h"
#include "parser/pg_trigger.h"

namespace peloton {
namespace commands {
Trigger::Trigger(peloton::planner::CreatePlan& plan) {

  trigger_name = plan.GetTriggerName();
  trigger_funcname = plan.GetTriggerFuncName();
  trigger_args = plan.GetTriggerArgs();
  trigger_columns = plan.GetTriggerColumns();
  trigger_when = plan.GetTriggerWhen();
  trigger_type = plan.GetTriggerType();
}

void TriggerList::AddTrigger(Trigger trigger) {
  triggers.push_back(trigger);
  UpdateTypeSummary(trigger.GetTriggerType());
}

void TriggerList::UpdateTypeSummary(int16_t type) {
  types_summary[BEFORE_INSERT_ROW] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_ROW, TRIGGER_TYPE_BEFORE, TRIGGER_TYPE_INSERT);
  types_summary[BEFORE_INSERT_STATEMENT] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_STATEMENT, TRIGGER_TYPE_BEFORE, TRIGGER_TYPE_INSERT);
  types_summary[BEFORE_UPDATE_ROW] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_ROW, TRIGGER_TYPE_BEFORE, TRIGGER_TYPE_UPDATE);
  types_summary[BEFORE_UPDATE_STATEMENT] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_STATEMENT, TRIGGER_TYPE_BEFORE, TRIGGER_TYPE_UPDATE);
  types_summary[BEFORE_DELETE_ROW] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_ROW, TRIGGER_TYPE_BEFORE, TRIGGER_TYPE_DELETE);
  types_summary[BEFORE_DELETE_STATEMENT] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_STATEMENT, TRIGGER_TYPE_BEFORE, TRIGGER_TYPE_DELETE);
  types_summary[AFTER_INSERT_ROW] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_ROW, TRIGGER_TYPE_AFTER, TRIGGER_TYPE_INSERT);
  types_summary[AFTER_INSERT_STATEMENT] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_STATEMENT, TRIGGER_TYPE_AFTER, TRIGGER_TYPE_INSERT);
  types_summary[AFTER_UPDATE_ROW] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_ROW, TRIGGER_TYPE_AFTER, TRIGGER_TYPE_UPDATE);
  types_summary[AFTER_UPDATE_STATEMENT] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_STATEMENT, TRIGGER_TYPE_AFTER, TRIGGER_TYPE_UPDATE);
  types_summary[AFTER_DELETE_ROW] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_ROW, TRIGGER_TYPE_AFTER, TRIGGER_TYPE_DELETE);
  types_summary[AFTER_DELETE_STATEMENT] |= TRIGGER_TYPE_MATCHES(type, TRIGGER_TYPE_STATEMENT, TRIGGER_TYPE_AFTER, TRIGGER_TYPE_DELETE);
}

}
}