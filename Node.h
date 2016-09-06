#include <vector>
#include <string>

using namespace std;

class Node
{
	public:
		Node(Node* parentNode, pair <int, int> sSide, pair<int, int> oSide, bool bDirection, string sDescription);
		~Node(void);

		// <Missonaries, Cannibals>
		pair <int, int> startingSide;
		pair <int, int> otherSide;

		//direction will be true for heading to other side, false for heading back
		bool direction;

		vector <Node*> children;
		Node* parent;

		bool isFinalState();
		bool isSafeState();
		bool isDuplicate();

		string description;

		void makeChildren();
};

