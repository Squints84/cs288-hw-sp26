#!/bin/bash

DATE=$(date +%Y%m%d)

BACKUP_DIR="backup $DATE"
mkdir "$BACKUP_DIR"

# $@ gives you arglist as separate strings
for FILE IN "$@"
do
	if [ -f "$FILE" ]; then
		cp "$FILE" "$BACKUP_DIR/$FILE.back.$DATE"
	else
		echo "Warning: $FILE does not exist and was skipped."
	fi
done

echo "Backup completed in directory: $BACKUP_DIR"

