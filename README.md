1.PageView Class: Represents a page view with a timestamp, page ID, and customer ID. It can be created from a log entry string and converted back to a string.

2.createSampleLogFile Function: Generates a log file from a list of PageView objects and writes it to a file.

3.readDataFromFile Function: Reads a log file and returns a map where each customer ID is mapped to a set of page IDs they visited.

4.Main Function:

	  1.Creates two sample log files (day1.log and day2.log) with page views.
	
	  2.Reads data from day1.log into a map.
	
	  3.Iterates through day2.log, identifying loyal customers who (a)  came on both days, and (b) visited at least two unique pages.
	
	  4.Prints out the IDs of loyal customers.
