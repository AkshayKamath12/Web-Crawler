General description: 

crawler.c takes in command line parameters for the seedURL, the directory, and the depth you want to go to. It validates the parameters and then starts the crawling process. The webpage for the seedURL is added to the bag of webpages to be crawled. It opens a file called 1 within the directory. That file stores the url, depth, and html of the seedURL (html is obtained by using the download function of url.c). Every other numbered file in the directory follows this format. 

crawler.c processes the html of the seedURL and finds links within the html. After verifying those links to see if they are internal to the seed and normalizeable, which are functions url.c provides, they are added to a linked list of webpages to be crawled. Any processed urls are added to a hashtable of urls that have been seen. The crawling process stops once the last url at the end of the highest depth is processed as a file. 
	
Compile and run by running the command make and entering "./runTest (seedURL) (directory you want files to be placed) (depth)"
