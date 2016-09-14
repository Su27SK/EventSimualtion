<?php
$rfilename = "../dealedLinkInfo.txt";
$wfilename_common = "_link.txt";
$rhandle = fopen($rfilename, "r");
while (!feof($rhandle)) {
	$buffer = fgets($rhandle, 4096);
	$match = array();
	preg_match_all("/\d+/", $buffer, $match);
	if (!empty($match[0])) {
		$wfilename = $match[0][1] . "_To_" . $match[0][2] . $wfilename_common;
		$whandle = fopen($wfilename, "a+");
		$info = $match[0][3] . "\n";
		fwrite($whandle, $info);
	}
}
