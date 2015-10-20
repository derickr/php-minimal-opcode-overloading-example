<?php
function test()
{
	try {
		throw new Exception();
	} catch (Exception $e) {
	}
	$a = 4;
	$a = $a * M_PI;
	$a = $a - 42;
}

test();
?>
==DONE==
