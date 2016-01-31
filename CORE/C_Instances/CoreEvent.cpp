#include "CoreEvent.h"

void CoreEvent::trigger()
{
	//Executes all Subjects in the subjectVector
	for each (Subject* s in subjectVector)
	{
		s->execute();
	}
}

CoreEvent::CoreEvent(Subject* originalSubject)
{
	subjectVector.push_back(originalSubject);
}