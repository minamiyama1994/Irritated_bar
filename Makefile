libs= \
	-l boost_program_options-mgw47-mt-$(BoostVersion).dll \
	-l boost_filesystem-mgw47-mt-$(BoostVersion).dll \
	-l boost_system-mgw47-mt-$(BoostVersion).dll \
	-l boost_thread-mgw47-mt-$(BoostVersion).dll \
	-l boost_serialization-mgw47-mt-$(BoostVersion).dll \
	-l icuuc.dll \
	` wx-config --libs `
all : exe_file
exe_file :
	+make libirritated_bar_interface.dll
	+make irritated_bar.exe
debug :
	+make all 'Options=$(DEBUGOptions)'
pre_release :
	+make all 'Options=$(PRERELEASEOptions)'
release :
	+make all 'Options=$(RELEASEOptions)'
clean :
	-rm --verbose *.o
	-rm --verbose *.s
	-rm --verbose *.ii
	-rm --verbose *.exe
	-rm --verbose *.dll
	-rm --verbose *.gcno
	-rm --verbose *.gcda
libirritated_bar_interface.dll : irritated_bar_interface.o
	$(CPP) -shared -o $@ $^ $(BIN_OPT) $(libs)
irritated_bar.exe : irritated_bar.o creater_manager.o
	$(CPP) -o $@ $^ $(BIN_OPT) $(libs) -L . -l irritated_bar_interface

include /local/tools/def.mak
include ./dep.mak