#include "renamepartundocommand.h"

using namespace MyPattern::CAD;

RenamePartUndoCommand::RenamePartUndoCommand(shared_ptr<PartDefinition> part, Glib::ustring old_name)
{
    m_renamedPart = part;
    m_old_name = old_name;
}

RenamePartUndoCommand::~RenamePartUndoCommand()
{
    //dtor
}

bool RenamePartUndoCommand::RunCommand()
{
    return m_renamedPart->set_name(m_old_name);
}
