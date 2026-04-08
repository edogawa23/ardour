#ifndef __gtk2_ardour_ghost_event_h__
#define __gtk2_ardour_ghost_event_h__

#include <memory>
#include <unordered_map>
#include <sigc++/trackable.h>

#include "evoral/Note.h"
#include "temporal/beats.h"

namespace ArdourCanvas {
	class Container;
	class Item;
	class Lollipop;
}

class NoteBase;


class GhostEvent : public sigc::trackable
{
   public:
	GhostEvent (::NoteBase *, ArdourCanvas::Lollipop* lolli);
	GhostEvent (::NoteBase *, ArdourCanvas::Item* parent);
	virtual ~GhostEvent ();

	void set_sensitive (bool yn);

	NoteBase* event;
	ArdourCanvas::Item* item;
	bool is_hit;
	int velocity_while_editing;

	/* must match typedef in NoteBase */
	typedef Evoral::Note<Temporal::Beats> NoteType;
	typedef std::unordered_map<std::shared_ptr<NoteType>, GhostEvent* > EventList;

	static GhostEvent* find (std::shared_ptr<NoteType> parent, EventList& events, EventList::iterator& opti);
};


#endif /* __gtk2_ardour_ghost_event_h__ */
