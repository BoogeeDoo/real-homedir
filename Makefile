UGLIFY_PATH=./node_modules/.bin/uglifyjs
MOCHA_PATH=./node_modules/.bin/_mocha
ISTANBUL_PATH=./node_modules/.bin/istanbul
COVERALLS_PATH=./node_modules/.bin/coveralls

test-coveralls:
	@$(ISTANBUL_PATH) cover $(MOCHA_PATH) \
		--report lcovonly \
		-- \
		-R spec && \
		cat ./coverage/lcov.info | \
		\
		$(COVERALLS_PATH) && \
		rm -rf ./coverage

test:
	@TRAVIS=true $(MOCHA_PATH) test/test.js

.PHONY: test test-coveralls
