#ifndef RENAMEPARTUNDOCOMMAND_H
#define RENAMEPARTUNDOCOMMAND_H

#include <partdefinition.h>
#include <memory>
#include <glibmm/ustring.h>

#include <undocommand.h>

using namespace MyPattern::Base;

namespace MyPattern
{
    namespace CAD
    {
        class RenamePartUndoCommand : public UndoCommand
        {
            public:
                RenamePartUndoCommand(shared_ptr<PartDefinition> part, Glib::ustring old_name);
                virtual ~RenamePartUndoCommand();
                bool RunCommand();
            protected:
            private:
                shared_ptr<PartDefinition> m_renamedPart;
                Glib::ustring m_old_name;
        };
    }
}



#endif // RENAMEPARTUNDOCOMMAND_H
