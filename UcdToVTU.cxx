#include <vtkAVSucdReader.h>
#include <vtkNew.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <string>


int main(int argc, char* argv[]) {

  // Parse command line arguments
  if(argc < 3)
  {
    std::cout << "Required arguments: InputFilename OutputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filenameIn = argv[1];
  std::string filenameOut = argv[2];

  // Read from AVS UCD data in binary form
  vtkNew<vtkAVSucdReader> reader;
  reader->SetFileName(filenameIn.c_str());
  reader->Update();

  // Write UCD data to VTU format
  vtkUnstructuredGrid* grid = vtkUnstructuredGrid::SafeDownCast(reader->GetOutput());

  // Write VTU file
  vtkNew<vtkXMLUnstructuredGridWriter> writer;
  writer->SetFileName(filenameOut.c_str());
  writer->SetInputData(grid);
  writer->Write();

  return EXIT_SUCCESS;
}
