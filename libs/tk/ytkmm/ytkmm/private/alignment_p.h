// -*- c++ -*-
// Generated by gmmproc 2.45.3 -- DO NOT MODIFY!
#ifndef _GTKMM_ALIGNMENT_P_H
#define _GTKMM_ALIGNMENT_P_H


#include <ytkmm/private/bin_p.h>

#include <glibmm/class.h>

namespace Gtk
{

class Alignment_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Alignment CppObjectType;
  typedef GtkAlignment BaseObjectType;
  typedef GtkAlignmentClass BaseClassType;
  typedef Gtk::Bin_Class CppClassParent;
  typedef GtkBinClass BaseClassParent;

  friend class Alignment;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
};


} // namespace Gtk


#endif /* _GTKMM_ALIGNMENT_P_H */

