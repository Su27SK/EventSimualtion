<?php
$rfilename = "TestFile.txt";
$wfilename = "DealedFile.txt";
$rhandle = fopen($rfilename, "r");
$whandle = fopen($wfilename, "w+"); 
list($mesc, $sec) = explode(' ', microtime());
srand($sec);
while (!feof($rhandle)) {
	$buffer = fgets($rhandle, 4096);
	$trans = array("\x0D" => "");
	$wOut = strtr($buffer, $trans);
	preg_match_all("/\w+/", $buffer, $out);
	if (!empty($out[0]) && $out[0][0] == 'L') {
		$weight = rand(10, 500);
		$wOut = $out[0][0] . " " . $out[0][1] . " " . $out[0][2] . " " . $out[0][3] . " " . $weight . "\n";
		echo $wOut;
	} 
	fwrite($whandle, $wOut); 
}
fclose($rhandle);
fclose($whandle);
