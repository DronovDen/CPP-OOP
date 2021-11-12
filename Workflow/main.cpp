#include "Workflow.h"

int main()
{
	std::string FileName = "workflow3.txt";
	Workflow executor;
	executor.execute(FileName);
	return 0;
}