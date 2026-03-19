#!/bin/bash

# Script to create test directory structure with email addresses
# for testing the email extraction script

# Base test directory
BASE_DIR="email_test_dir"

# Remove existing test directory if it exists
if [ -d "$BASE_DIR" ]; then
    echo "Removing existing test directory..."
    rm -rf "$BASE_DIR"
fi

echo "Creating directory structure..."

# Create directory structure
mkdir -p "$BASE_DIR"
mkdir -p "$BASE_DIR/subdir1"
mkdir -p "$BASE_DIR/subdir1/nested1"
mkdir -p "$BASE_DIR/subdir2"
mkdir -p "$BASE_DIR/subdir2/nested2/deep"
mkdir -p "$BASE_DIR/subdir3"
mkdir -p "$BASE_DIR/empty_dir"

echo "Creating text files with email addresses..."

# ============================================
# Files in ROOT directory
# ============================================

# File 1: Mix of valid emails and duplicates
cat > "$BASE_DIR/emails1.txt" << 'EOF'
john.doe@example.com
jane_smith@company.org
admin@website.net
john.doe@example.com
test123@domain.co.uk
user_name@sub-domain.com
EOF

# File 2: Valid emails with numbers and special chars
cat > "$BASE_DIR/contacts.txt" << 'EOF'
alice123@university.edu
bob-wilson@tech.io
charlie_99@sample.net
david.brown@email.com
emma_2024@service.org
EOF

# File 3: Mix of valid and INVALID emails
cat > "$BASE_DIR/mixed_data.txt" << 'EOF'
valid.email@domain.com
@invalid.com
user@
123startswithnumber@domain.com
user@domain
user@.com
special!char@domain.com
user name@domain.com
normal_user@valid.edu
EOF

# Non-txt file (should be ignored)
cat > "$BASE_DIR/readme.md" << 'EOF'
# README
This is a markdown file, not a txt file.
contact@example.com
This email should NOT be extracted.
EOF

# ============================================
# Files in subdir1
# ============================================

cat > "$BASE_DIR/subdir1/list1.txt" << 'EOF'
frank@company.com
george_123@university.edu
helen.jones@tech.io
jane_smith@company.org
irene-lee@domain.net
EOF

cat > "$BASE_DIR/subdir1/list2.txt" << 'EOF'
john.doe@example.com
kate@sample.com
admin@website.net
laura_m@email.org
EOF

# File with invalid emails
cat > "$BASE_DIR/subdir1/invalid_emails.txt" << 'EOF'
no-at-sign.com
user@@double.com
@startswithat.com
.startswith.dot@domain.com
user@domain..doubledot
user@-domain.com
valid_before@domain.com
-startwithdash@domain.com
EOF

# ============================================
# Files in nested1 (deeper level)
# ============================================

cat > "$BASE_DIR/subdir1/nested1/deep_contacts.txt" << 'EOF'
mike.wilson@deep.net
nancy_123@nested.edu
oliver-p@example.com
paula.r@university.org
EOF

cat > "$BASE_DIR/subdir1/nested1/more_emails.txt" << 'EOF'
quinn@sample.io
rachel_456@company.com
steve.jones@tech.net
alice123@university.edu
EOF

# ============================================
# Files in subdir2
# ============================================

cat > "$BASE_DIR/subdir2/users.txt" << 'EOF'
tom_2024@service.com
uma.patel@domain.org
victor-h@email.net
wendy@company.edu
EOF

cat > "$BASE_DIR/subdir2/subscribers.txt" << 'EOF'
xander_x@sample.com
yara.z@university.io
zachary@tech.org
admin@website.net
frank@company.com
EOF

# ============================================
# Files in nested2/deep (very deep level)
# ============================================

cat > "$BASE_DIR/subdir2/nested2/deep/archive.txt" << 'EOF'
adam.smith@archive.com
betty_old@legacy.net
charles-ancient@history.edu
diane@oldsite.org
EOF

cat > "$BASE_DIR/subdir2/nested2/deep/backup.txt" << 'EOF'
john.doe@example.com
test123@domain.co.uk
emma_2024@service.org
EOF

cat > "$BASE_DIR/subdir2/nested2/database.txt" << 'EOF'
user1@db.com
user2@db.com
user3@db.com
admin@db.com
EOF

# ============================================
# Files in subdir3
# ============================================

cat > "$BASE_DIR/subdir3/clients.txt" << 'EOF'
client_a@business.com
client_b@business.com
client_c@business.net
partner@enterprise.org
EOF

cat > "$BASE_DIR/subdir3/partners.txt" << 'EOF'
partner_1@global.com
partner_2@global.com
vendor@supply.net
contractor@services.io
EOF

# File with only invalid emails
cat > "$BASE_DIR/subdir3/garbage.txt" << 'EOF'
not-an-email
123@456
@@@
user@
@domain.com
....@domain.com
EOF

# Non-txt file (should be ignored)
cat > "$BASE_DIR/subdir3/data.csv" << 'EOF'
name,email
John,john@example.com
Jane,jane@example.com
EOF

echo ""
echo "=========================================="
echo "Setup Complete!"
echo "=========================================="
echo ""
echo "Test directory created: $BASE_DIR"
echo ""
# Count total .txt files
txt_files=$(find "$BASE_DIR" -name "*.txt" -type f | wc -l)
echo "Total .txt files created: $txt_files"

# Count non-.txt files (should be ignored)
non_txt_files=$(find "$BASE_DIR" -type f ! -name "*.txt" | wc -l)
echo "Non-.txt files (should be ignored): $non_txt_files"
