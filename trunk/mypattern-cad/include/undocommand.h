#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

namespace MyPattern
{
    namespace CAD
    {
        /** \brief A class that implements the command pattern to perform undo
        * operations
        *
        * This class and its ancestors add undo functionality to the CAD window
        * by means of the command pattern. This class defines he interface to
        * access the undo steps. UndoCommandQueue maintains a list of objects of
        * classes derived of this object. If an undo action is requested, the
        * object last added to the queue is executed and removed from the queue
        */
        class UndoCommand
        {
            public:
                virtual bool RunCommand() = 0;
            protected:
            private:
        };
    }
}


#endif // UNDOCOMMAND_H
