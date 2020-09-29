#include <string>
#include <sstream>
#include <iterator>

using namespace std;

template <class Container>
void split(const string& linha, Container& cont){
    istringstream iss(linha);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}