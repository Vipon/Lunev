//*************//
//Made by Vipon//
//*************//

typedef struct Dpoint {
	
	double minX;
	double maxX;
	char  *minY;
	char  *maxY;

} Dpoint;

typedef struct argI {

	char *func;
	Dpoint *p;
} argI;

double *dIntegral ( argI *arg );
