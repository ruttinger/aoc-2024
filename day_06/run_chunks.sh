#!/bin/bash

# Loop through the chunk indexes (0 to 129)
for i in {0..129}; do
  # Run each Docker container in the background (-d) and pass CHUNK_INDEX as an environment variable
  docker run -d -e CHUNK_INDEX=$i grid_program
done
