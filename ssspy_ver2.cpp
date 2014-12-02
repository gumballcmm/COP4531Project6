//revised by Carlos 12/1/2014

#include <iostream>
#include <fstream>
#include <compare_spy.h>
#include <compare.h>
#include "lsb.h"
#include "msb.h"
#include "qs3w.h"
#include "genalg.h"
#include "vector.h"
#include <timer.h>
#include <string>
//#include "stringsort_type.h"

typedef uint8_t CharType;
const size_t logR = 8;
const size_t R = 256;

/*
//Binary
typedef uint8_t CharType;
const size_t logR = 1;
const size_t R = 2;

*/

/*
//Decimal
typedef uint8_t CharType;
const size_t logR = 4;
const size_t R = 10;
*/

/*
//DNA
typedef uint8_t CharType;
const size_t logR = 2;
const size_t R = 4;
*/

/*
//Unicode
typedef uint16_t CharType;
const size_t logR = 16;
const size_t R = 65536;
*/

/*
//Uppercase
typedef uint8_t CharType;
const size_t logR = 5;
const size_t R = 26;
*/

void WriteSortedResultsFile(CharType * data, size_t length, std::string filename);

int main(int argc, char* argv[])
{
  /* Make sure command line arguments are ok. */
  if(argc < 3)
  {
    std::cout << " ** command line arguments:" << std::endl
              << "     1: input filename (required)" << std::endl
        << "     2: output filename (required) [This will output a file with the timing results," << std::endl
        << "                                    and also files with the sorted results, with extensions" << std::endl
        << "                                    .LSB, .MSB, and .3WQS." << std::endl
              << " ** try again" << std::endl;
    return 0;
  }

  /* Make sure we can open the specified input file of strings to sort. */
  std::string infile = argv[1];
  std::ifstream instream(infile);
  if(instream.fail())
  {
    std::cout << " ** cannot open file " << infile << " for read"
         << std::endl << " ** try again" << std::endl;
    return 0;
  }

  /* Make sure we can open the specified output file. */
  std::string outfile = argv[2];
  std::ofstream outstream(outfile);
  if(outstream.fail())
  {
    std::cout << " ** cannot open file " << outstream << " for write"
         << std::endl << " ** try again" << std::endl;
    return 0;
  }

  /* The less than spy used to determine how many comparisons were done as part
     of the sort. */
  fsu::LessThanSpy<CharType> lts;

  /* The timer information. */
  fsu::Instant instant;
  fsu::Timer timer;



 /* Get the source data strings from the input file. */
  fsu::Vector<CharType> source_data;
  size_t item;
  while(instream >> item)
  {
    source_data.PushBack((CharType)item);
  }
  CharType * data = new CharType[source_data.Size()];

  /* Close instream. */
  instream.close();

  /******************** LSB Sort ********************/

  /* Create the LSB class with the specified alphabet. */
  LSB<CharType> lsb(R, logR);

  /* Populate the data array to be sorted. */
  fsu::g_copy(source_data.Begin(), source_data.End(), data);

  /* Reset comparison count. */
  lts.Reset();

  /* Perform and time the LSB sort. */
  timer.SplitReset();
  lsb.Sort(data, source_data.Size(), lts);
  instant = timer.SplitTime();

  /* Output pertinent data. */
  outstream << "LSB sort." << std::endl;
  outstream << "time (seconds): " << instant.Get_seconds() << std::endl;
  outstream << "time (useconds): " << instant.Get_useconds() << std::endl;
  outstream << "comparisons: " << lts.Count() << std::endl;
  outstream << std::endl;

  /* Write sorted results. */
  WriteSortedResultsFile(data, source_data.Size(), outfile + std::string(".LSB"));

  /******************** MSB Sort ********************/

  /* Create the MSB class with the specified alphabet. */
  MSB<CharType> msb(R, logR);

  /* Populate the data array to be sorted. */
  fsu::g_copy(source_data.Begin(), source_data.End(), data);

  /* Reset comparison count. */
  lts.Reset();

  /* Perform and time the MSB sort. */
  timer.SplitReset();
  msb.Sort(data, source_data.Size(), lts);
  instant = timer.SplitTime();


 /* Output pertinent data. */
  outstream << "LSB sort." << std::endl;
  outstream << "time (seconds): " << instant.Get_seconds() << std::endl;
  outstream << "time (useconds): " << instant.Get_useconds() << std::endl;
  outstream << "comparisons: " << lts.Count() << std::endl;
  outstream << std::endl;

  /* Write sorted results. */
  WriteSortedResultsFile(data, source_data.Size(), outfile + std::string(".LSB"));

  /******************** MSB Sort ********************/

  /* Create the MSB class with the specified alphabet. */
  MSB<CharType> msb(R, logR);

  /* Populate the data array to be sorted. */
  fsu::g_copy(source_data.Begin(), source_data.End(), data);

  /* Reset comparison count. */
  lts.Reset();

  /* Perform and time the MSB sort. */
  timer.SplitReset();
  msb.Sort(data, source_data.Size(), lts);
  instant = timer.SplitTime();

  /* Output pertinent data. */
  outstream << "MSB sort." << std::endl;
  outstream << "time (seconds): " << instant.Get_seconds() << std::endl;
  outstream << "time (useconds): " << instant.Get_useconds() << std::endl;
  outstream << "comparisons: " << lts.Count() << std::endl;
  outstream << std::endl;

  /* Write sorted results. */
  WriteSortedResultsFile(data, source_data.Size(), outfile + std::string(".MSB"));

  /******************** 3WQS Sort ********************/

  /* Create the MSB class with the specified alphabet. */
  QS3W<CharType> qs3w(R, logR);

  /* Populate the data array to be sorted. */
  fsu::g_copy(source_data.Begin(), source_data.End(), data);

  /* Reset comparison count. */
  lts.Reset();

  /* Perform and time the 3WQS sort. */
  timer.SplitReset();
  qs3w.Sort(data, source_data.Size(), lts);
  instant = timer.SplitTime();

  /* Output pertinent data. */
  outstream << "3WQS sort." << std::endl;
  outstream << "time (seconds): " << instant.Get_seconds() << std::endl;
  outstream << "time (useconds): " << instant.Get_useconds() << std::endl;
  outstream << "comparisons: " << lts.Count() << std::endl;
  outstream << std::endl;


  /* Write sorted results. */
  WriteSortedResultsFile(data, source_data.Size(), outfile + std::string(".3WQS"));

  /* Close file. */
  outstream.close();

  return 0;
}

void WriteSortedResultsFile(CharType * data, size_t length, std::string filename)
{
  std::ofstream outstream(filename);

  if (outstream.fail())
  {
    std::cout << " ** cannot open file " << filename << " for write\n"
        << " ** try again\n";
    return;
  }

  for(size_t i = 0; i < length; i++)
  {
    outstream << (size_t)data[i] << std::endl;
  }

  outstream.close();
}



