# Run whole system at once!
#!/bin/bash
gnome-terminal --title="DATA PROVIDER" -- bash -c "./data_provider 1"
sleep .5
gnome-terminal --title="DATA PROCESSING" -- bash -c "./data_processing"
sleep .5
gnome-terminal --title="DATA ARCHIVER" -- bash -c "./data_archiver"