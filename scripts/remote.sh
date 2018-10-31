#!/bin/bash

# number of frames to render
NB_FRAMES=120

nb_hosts=0
while read host ; do
    nb_hosts=$((nb_hosts + 1))
done < scripts/hosts.list


echo "---" $nb_hosts "hosts found"
echo "--- Update remote sources"

while read host ; do
    ssh -n $host 'rm -rf /tmp/jelly && mkdir -p /tmp/jelly' &
done < scripts/hosts.list

wait

while read host ; do
    echo $host
    rsync --exclude-from '.gitignore' --exclude '.git' -au ./ $host:/tmp/jelly &
done < scripts/hosts.list

wait

echo "--- Build frames"
host_id=0

while read host ; do
    start=$((host_id * (NB_FRAMES / nb_hosts)))
    end=$(((host_id + 1) * (NB_FRAMES / nb_hosts) - 1))

    echo $host ":" $start "to" $end

    command='cd /tmp/jelly && make clean && make release'
    for i in `seq $start $end` ; do
        i=$(printf "%03d" $i)
        command=$command" && nohup make POV_ARGS=+WT7 FRAME=${i} scene > /dev/null"
    done
    echo $command
    ssh -n $host "${command}" &

    host_id=$((host_id + 1))
done < scripts/hosts.list

wait
clear

echo "--- Collect frames"

rm -r frames
while read host ; do
    mkdir -p frames/$host
    scp $host:/tmp/jelly/scene_frame*.png frames/$host &
done < scripts/hosts.list

wait

echo "--- Building .gif"
convert frames/*/scene_frame_*.png scene.gif

# ssh info 'cd /tmp/jelly && make FRAME=1 scene && make FRAME=2 scene'
