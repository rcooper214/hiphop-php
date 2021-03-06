--TEST--
Test tempnam() function: usage variations - creating files 
--SKIPIF--
<?php
if(substr(PHP_OS, 0, 3) == "WIN")
  die("skip Do not run on Windows");
?>
--FILE--
<?php
/* Prototype:  string tempnam ( string $dir, string $prefix );
   Description: Create file with unique file name.
*/

/* Creating number of unique files by passing a file name as prefix */

$file_path = dirname(__FILE__);

echo "*** Testing tempnam() in creation of unique files ***\n";
for($i=1; $i<=10; $i++) {
  echo "-- Iteration $i --\n";
  $files[$i] = tempnam("$file_path", "tempnam_variation1.tmp");

  if( file_exists($files[$i]) ) { 

    echo "File name is => "; 
    print($files[$i]);
    echo "\n";
  
    echo "File permissions are => ";
    printf("%o", fileperms($files[$i]) );
    echo "\n";
    clearstatcache();

    echo "File inode is => ";
    print_r( fileinode($files[$i]) ); //checking inodes
    echo "\n";
    clearstatcache();
  }
  else {
    print("- File is not created -");
  }
}
for($i=1; $i<=10; $i++) {
  unlink($files[$i]);
}

echo "*** Done ***\n";
?>
--EXPECTF--
*** Testing tempnam() in creation of unique files ***
-- Iteration 1 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 2 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 3 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 4 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 5 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 6 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 7 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 8 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 9 --
File name is => %s
File permissions are => 100600
File inode is => %d
-- Iteration 10 --
File name is => %s
File permissions are => 100600
File inode is => %d
*** Done ***
