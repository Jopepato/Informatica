%We are going to load all the files and pass them throught the neuronal
%network


%Later we will change the train and test part of the files in order to test
%our neuronal network with more types of exercises.



%We are going to read the the folders and make a vector with each one, but
%only with the 10000 first bits of each file

%vectorDll = [];
%vectorOutputDll = [];
%vectorImages = [];
%vectorOutputImages = [];
%vectorShell = [];
%vectorOutputShell = [];

inputVector = [];
outputVector = [];
files = dir('IDSdata/DLL/');
cd IDSdata/DLL/

for i=3:length(files)
    file = fopen(files(i).name);
    fileAux = fread(file);
    fclose(file);
    inputVector = [inputVector, fileAux(1:200,:)];
    outputVector = [outputVector, 1];
end
cd ../..
files = dir('IDSdata/IMAGES/');
cd IDSdata/IMAGES/

for i=3:length(files)
    file = fopen(files(i).name);
    fileAux = fread(file);
    fclose(file);
    inputVector = [inputVector, fileAux(1:200,:)];
    outputVector = [outputVector, 2];
end


cd ../..
files = dir('IDSdata/SHELL/');
cd IDSdata/SHELL/

for i=3:length(files)
    file = fopen(files(i).name);
    fileAux = fread(file);
    fclose(file);
    inputVector = [inputVector, fileAux(1:200,:)];
    outputVector = [outputVector, 3];
end

cd ../..

%Now we have the vector with the files, but only with the first 2249 bits
%as we can't take more because that is the minimum of the image, and if we
%take more we would have to fill that ghostly bits  with some imaginary
%values

nntool