#include <vtkAVSucdReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkGeometryFilter.h>
#include <string>
#include <fstream>


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
  vtkSmartPointer<vtkAVSucdReader> reader = vtkSmartPointer<vtkAVSucdReader>::New();
  reader->SetFileName(filenameIn.c_str());
  reader->Update();

  // Write UCD data to VTU format
  vtkUnstructuredGrid* grid = vtkUnstructuredGrid::SafeDownCast(reader->GetOutput());

  // Extract geometry from vtkUnstructuredGrid
  vtkSmartPointer<vtkGeometryFilter> geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
  geometryFilter->SetInputData(grid);
  geometryFilter->Update();

  // Write VTU file
  vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetFileName(filenameOut.c_str());
  writer->SetInputData(geometryFilter->GetOutput());
  writer->Write();

  return EXIT_SUCCESS;
}
