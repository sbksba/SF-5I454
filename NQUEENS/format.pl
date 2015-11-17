#!/usr/bin/perl -w
#formal.pl

use strict;
use warnings;

my $filename = $ARGV[0];           # store the 1st argument into the variable
my $size=$ARGV[1];
open my $fh, '<', $filename or die $!;

my $cpt = 0;
my $quit = 0;

while (my $row = <$fh>) {
    next if $. < 2;
    chomp $row;
    $row =~ s/-\d+/-/g;
    
    foreach my $char (split / /, $row) {
	if ($quit == ($size*$size)) {
	    print "\n";
	    exit 0;
	}
	if ($cpt == $size) {
	    print "\n";
	    $cpt = 0;
	}
	if ($char ne '-') {
	    print " Q";
	}
	else {
	    print " $char";
	}
	$cpt++;
	$quit++;
    }
}
