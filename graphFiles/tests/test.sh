#!/bin/bash

function getInfoFromFile
{
	echo $(cat $1)
}

function check
{
	if [ "$1" == "$2" ]; then
		echo $3
	else
		echo $4
		echo "Test:"
		echo $1
        echo $2
		exit 2
	fi
}

presentDirectory=$(dirname $0)
allShortestPathsDirecotry=build
testDirectory=tests/graphTest
artifactsDirectory=tests/artifacts
graphTestDirectory=tests/graphTest
graphsDirectory=tests/graphs

cd $presentDirectory
mkdir artifacts

cd artifacts
touch randomVertices.txt
touch answerCircle.txt
touch answerMatrix.txt
touch answerShortestPath.txt

#test1
cd ../..

count=1

for i in {1..100}
do
	$graphTestDirectory/randomVertices $artifactsDirectory/randomVertices.txt Circle

	$allShortestPathsDirecotry/allShortestPaths $graphsDirectory/circleGraph.txt $artifactsDirectory/randomVertices.txt $artifactsDirectory/answerShortestPath.txt

	$graphTestDirectory/testCircle $artifactsDirectory/randomVertices.txt $artifactsDirectory/answerCircle.txt

	circleLength=$(getInfoFromFile $artifactsDirectory/answerCircle.txt)
	allShortestPathslength=$(wc -w < $artifactsDirectory/answerShortestPath.txt)

	echo -n "$count: "
	check "$circleLength" "$allShortestPathslength" "+ passed: Circle" "- TEST FAILED: Circle."

	count=$((count+1))
done

#test 2
count=1

for i in {1..100}
do
	$graphTestDirectory/randomVertices $artifactsDirectory/randomVertices.txt Matrix

	$allShortestPathsDirecotry/allShortestPaths $graphsDirectory/matrixGraph.txt $artifactsDirectory/randomVertices.txt $artifactsDirectory/answerShortestPath.txt

	$graphTestDirectory/testMatrix $artifactsDirectory/randomVertices.txt $artifactsDirectory/answerMatrix.txt

	circleLength=$(getInfoFromFile $artifactsDirectory/answerMatrix.txt)
	allShortestPathslength=$(wc -l < $artifactsDirectory/answerShortestPath.txt)

	echo -n "$count: "
	check "$circleLength" "$allShortestPathslength" "+ passed: Matrix" "- TEST FAILED: Matrix."

	count=$((count+1))
done

cd ..
rm -rf ./artifacts