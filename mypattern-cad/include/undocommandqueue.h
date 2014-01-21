#ifndef UNDOCOMMANDQUEUE_H
#define UNDOCOMMANDQUEUE_H

#include <memory>

using namespace std;

namespace MyPattern
{
    namespace CAD
    {
        class UndoCommandQueue
        {
            public:

                virtual ~UndoCommandQueue();

                static shared_ptr<UndoCommandQueue> GetInstance();
            protected:
            private:
                UndoCommandQueue();
                static shared_ptr<UndoCommandQueue> s_instance;
                bool s_has_instance = false;
        };
    }
}


#endif // UNDOCOMMANDQUEUE_H
