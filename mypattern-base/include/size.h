#ifndef SIZE_H
#define SIZE_H

namespace MyPattern
{
    namespace Base
    {
        class Size
        {
            public:
                Size();
                Size(float width, float height);
                virtual ~Size();
                float get_width() { return m_width; }
                void set_width(float val) { m_width = val; }
                float get_height() { return m_height; }
                void set_height(float val) { m_height = val; }
            protected:
            private:
                float m_width;
                float m_height;
        };
    }
}


#endif // SIZE_H
