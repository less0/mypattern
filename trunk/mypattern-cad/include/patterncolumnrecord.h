#ifndef PATTERNCOLUMNRECORD_H
#define PATTERNCOLUMNRECORD_H

#include <gtkmm/treemodel.h>
#include <patterndefinition.h>
#include <memory>


class PartColumnRecord : public Gtk::TreeModel::ColumnRecord
{
    public:
        PartColumnRecord()
        {
            add(column_name);
			add(column_pattern);
        }

        Gtk::TreeModelColumn<Glib::ustring> column_name;
        Gtk::TreeModelColumn<shared_ptr<MyPattern::Base::PatternDefinition>> column_pattern;
    protected:
    private:
};

#endif // PATTERNCOLUMNRECORD_H
