#include "main.hh"
#include <string>
// simple tool for converting trajectory from datafile to plottable txt 




void convert(char* filename);

int main( int argc, char ** argv) {
  
  if(argc <2 ) { 
   cout << " usage: " << argv[0] << " [trajectory file .dat]"<<endl; 
   return -1;
  }
  
  for( int i = 1 ; i < argc ; i++) { 
    
    convert(argv[i]);
  
  }
  
  return 0;
};

void convert(char* file) {
  
  string filename(file);
  string outFile = filename;
  outFile.erase(filename.length()-3) ;
  outFile.append("txt");
  cout << "converting " << filename << " to " << outFile << endl;
  
  
  Datafile *f = Datafile::open(filename.c_str());
  
  
  if(!f->ok()) {
   return; 
  }
  
  int count = f->getCount()/2;
  cout << " count: " << count << endl;
  
  
  ofstream output(outFile.c_str());
  
  double dt = 0.001;
  for(int i = 0; i < count ; i++) {
  
  
    output << dt * i <<"\t";
    output << f->read();
    output << "\t";
    output << f->read();
    output << "\n";
    
  }
  
  output.close();
  
  f->close();
  
}