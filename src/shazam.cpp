#include "shazam.hpp"

#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <output .gz file>" << endl;
    }

    ifstream infile(argv[1], ios_base::in | ios_base::binary);

    // char* str = "Hello";
    // char dest[12];

    // strcpy( dest, str );
    // ;

    // Read filename from the first command line argument
    ofstream outfile(strcat(argv[1], ".gz"), ios_base::out | ios_base::binary);
    boost::iostreams::filtering_streambuf<boost::iostreams::output> outbuf;
    outbuf.push(boost::iostreams::gzip_compressor());
    outbuf.push(infile);
    // Convert streambuf to ostream
    ostream out(&outbuf);
    // Write some test data
    out << "This is a test text!\n";
    // Cleanup
    boost::iostreams::close(outbuf); // Don't forget this!
    outfile.close();
    infile.close();

    return 0;
}