make -j8
nvidia-settings --load-config-only --assign="SyncToVBlank=0"  # disable vertical sync
./bin/robotsim
nvidia-settings --load-config-only