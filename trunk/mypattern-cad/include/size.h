#ifndef SIZE_H
#define SIZE_H


class Size
{
    public:
        Size();
        virtual ~Size();
        unsigned float Getwidth() { return m_width; }
        void Setwidth(unsigned float val) { m_width = val; }
        unsigned float Getheight() { return m_height; }
        void Setheight(unsigned float val) { m_height = val; }
    protected:
    private:
        unsigned float m_width;
        unsigned float m_height;
};

#endif // SIZE_H
