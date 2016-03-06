<<<<<<< HEAD
UGLIFY_PATH=./node_modules/.bin/uglifyjs
=======
>>>>>>> becfae14a6202cc332caefa9ed94ad6fdb638a31
MOCHA_PATH=./node_modules/.bin/_mocha
ISTANBUL_PATH=./node_modules/.bin/istanbul
COVERALLS_PATH=./node_modules/.bin/coveralls

test-coveralls:
<<<<<<< HEAD
	@$(ISTANBUL_PATH) cover $(MOCHA_PATH) \
=======
	@TRAVIS=true $(ISTANBUL_PATH) cover $(MOCHA_PATH) \
>>>>>>> becfae14a6202cc332caefa9ed94ad6fdb638a31
		--report lcovonly \
		-- \
		-R spec && \
		cat ./coverage/lcov.info | \
		\
		$(COVERALLS_PATH) && \
		rm -rf ./coverage

test:
	@TRAVIS=true $(MOCHA_PATH) test/test.js

<<<<<<< HEAD
.PHONY: test test-coveralls
=======

.PHONY: test test-coveralls
>>>>>>> becfae14a6202cc332caefa9ed94ad6fdb638a31
