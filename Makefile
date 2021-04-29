clean:
	find . -type f -name 'vgcore*' -delete
	find . -type f -name 'a.out' -delete
	find . -type f -name '*.o' -delete

count:
	find . -name '*.cpp' | xargs wc -l
	find . -name '*.h' | xargs wc -l
	find . -name '*.md' | xargs wc -l