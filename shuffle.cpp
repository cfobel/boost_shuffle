#include <iostream>
#include <vector>
#include <time.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/iterator/counting_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/foreach.hpp>


using namespace std ;

struct timespec time1;

boost::mt19937 gen;
typedef boost::counting_iterator<int> _i;
typedef boost::iterator_range<_i> int_range;
#define make_range boost::make_iterator_range
#define range(x,y) make_range(_i(x), _i(y))

int main( int argc, char* argv[] ) {
    vector<int> my_list(10);
//    int_range my_range = range(_i(0), _i(my_list.size()));
    int_range my_range = range(0, my_list.size());
    int temp;
    int p1, p2;

    boost::uniform_int<> dist(0, my_list.size() - 1);
    clock_gettime(CLOCK_REALTIME, &time1);
    gen = boost::mt19937(time1.tv_nsec);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);

    BOOST_FOREACH(int i, my_range) {
        my_list[i] = i;
    }

    cout << "Original list:" << endl;
    BOOST_FOREACH(int i, my_range) {
        cout << "    " << my_list[i] << endl;
    }

    BOOST_FOREACH(int i, my_range) {
        p1 = die();
        p2 = die();
        if(p1 != p2) {
            temp = my_list[p1];
            my_list[p1] = my_list[p2];
            my_list[p2] = temp;
        }
    }

    cout << "Shuffled list:" << endl;
    BOOST_FOREACH(int i, my_range) {
        cout << "    " << my_list[i] << endl;
    }

    return 0;
}
