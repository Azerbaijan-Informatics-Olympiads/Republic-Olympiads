#include <cstdio>
#include <cstdlib>
#include <vector>
#include "testlib.h"

using namespace std;

long long gcd(long long a,long long b){
	return (b==0)?a:gcd(b,a%b);
}

int used[1000002];

int main(int argc, char* argv[]){
registerTestlibCmd(argc,argv);
//Reading data
int a_mx = ans.readInt(1,1000000,"The max limit of a[i]");
int n_in = inf.readInt(3,100000,"N from input");
vector<int>ans = ouf.readInts(n_in,1,a_mx,"Answer of the participant");

//Initializing
long long gcd_all;
long long sum_of_array=0;

for(int i=0;i<(int)ans.size();i++)
{
	//Checking the unique property of array
  if(used[ans[i]])quitf(_wa, "Violate the rule (array must be unique)");
	used[ans[i]]=1;

	//Finding the gcd of all array
	gcd_all=((i==0)?ans[i]:gcd(gcd_all,ans[i]));

	//Finding the sum of all array
	sum_of_array+=ans[i];
}

//Checking the last rule
if(gcd_all!=1){
	quitf(_wa, "Violate the rule (GCD of array must be 1)");
}

//Checking the second rule
for(int i=0;i<(int)ans.size();i++)
{
  if(gcd(sum_of_array-ans[i],ans[i])==1)quitf(_wa, "Violate the rule (GCD must be bigger than 1)");
}

//Finished checking
quitf(_ok, "Correct answer");

return 0;
}
