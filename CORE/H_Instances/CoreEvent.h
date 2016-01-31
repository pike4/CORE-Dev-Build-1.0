#include <vector>
#include "Subject.h"

//Event wrapper to allow events to be decoupled from their Subjects, i.e. rebindable keys
class CoreEvent
{
public:

	//Vector of subjects to be triggered when this CoreEvent occurs
	std::vector <Subject*> subjectVector;

	//Executes all Subjects in the subjectVector
	void trigger();

	//Create a new CoreEvent with a single Subject attached
	CoreEvent(Subject* originalSubject);
};

