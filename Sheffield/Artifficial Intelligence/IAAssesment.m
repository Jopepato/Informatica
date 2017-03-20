%We are going to load all the files and pass them throught the neuronal
%network


%Later we will change the train and test part of the files in order to test
%our neuronal network with more types of exercises.



%We are going to load the three different files and plot them

file = fopen('IDSdata/DLL/ABOUTWEP.DLL', 'r');
fileDll = fread(file);
fclose(file);
figure(1)
subplot(1,3,1);
plot(fileDll);

file = fopen('IDSdata/IMAGES/Im001.jpg', 'r');
fileJpg = fread(file);
fclose(file);
subplot(1,3,2);
plot(fileJpg);


file = fopen('IDSdata/SHELL/13244.c.execute', 'r');
fileShell = fread(file);
fclose(file);
subplot(1,3,3);
plot(fileShell);