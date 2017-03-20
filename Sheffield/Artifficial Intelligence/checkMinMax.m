%We are going to check the min and max number of bits of every type of file

%First for the dll
files = dir('IDSdata/SHELL/');
cd IDSdata/SHELL/
DllVector = [];
minBits = 5000;
maxBits = 5000;
for i=3:length(files)
    file = fopen(files(i).name);
    fileAux = fread(file);
    fclose(file);
    %DllVector = [DllVector, fileAux];
    %We are going to check now the number of bits
    if size(fileAux, 1) > maxBits
        maxBits = size(fileAux,1);
    else if size(fileAux,1) < minBits
            minBits = size(fileAux,1);
        end
    end
end

cd ../..