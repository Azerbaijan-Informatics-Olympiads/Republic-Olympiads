#include <cstdio>
#include <cstdlib>
#include <vector>
#include "testlib.h"

using namespace std;

int gcd(int a,int b){
	return (b==0)?a:gcd(b,a%b);
}

int used[1000002];

int main(int argc, char* argv[]){
registerTestlibCmd(argc,argv);
int a_mx = ans.readInt(1,1000000,"The max limit of a[i]");
int n_in = inf.readInt(3,100000,"N from input");
vector<int>ans = ouf.readInts(n_in,1,a_mx,"Answer of the participant");
int gcd_all;
int sum_of_array=0;
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

if(gcd_all!=1){
	quitf(_wa, "Violate the rule (GCD of array must be 1)");
}

for(int i=0;i<(int)ans.size();i++)
{
  if(gcd(sum_of_array-ans[i],ans[i])==1)quitf(_wa, "Violate the rule (GCD must be bigger than 1)");
}

quitf(_ok, "Correct answer");

return 0;
}
