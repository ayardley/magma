
/**
 * @file /magma/src/providers/prime/messages/chunks/chunks.c
 *
 * @brief DESCRIPTIONxxxGOESxxxHERE
 *
 * $Author$
 * $Date$
 * $Revision$
 *
 */

#include "magma.h"

uint32_t chunk_header_size(stringer_t *chunk) {
#error unfinished
}

prime_message_chunks_t chunk_header_type(stringer_t *chunk) {

	size_t len = 0;
	uint8_t type = 0;
	uchr_t *data = NULL;
	prime_message_chunks_t result = PRIME_CHUNK_NONE;

	if (st_empty_out(chunk, &data, &len)) {
		log_pedantic("The chunk buffer is invalid.");
		return result;
	}

	type = *((uint8_t *)data);

	switch(type) {
		case PRIME_CHUNK_EPHEMERAL:
			result = PRIME_CHUNK_EPHEMERAL;
			break;

		default
		#error unfinished
	};
	return result;
}


stringer_t * chunk_header_write(prime_message_chunks_t type, size_t size, stringer_t *output) {

	stringer_t *result = NULL;
	uint32_t big_endian_size = htobe32(size);

	// Ensure the chunk payload is less than (2^24) - 1, or 16,777,215 in length.
	if (PRIME_MAX_3_BYTE < size) {
		log_error("The size provided is too large for the specified PRIME chunk type. { type = %i / max = %i / size = %zu }",
			type, PRIME_MAX_3_BYTE, size);
		return NULL;
	}

	// Check whether the buffer is valid, or if output is NULL, allocate a buffer to hold the output.
	else if (!(result = st_output(output, 4))) {
		log_pedantic("An output buffer could not be setup to hold the result.");
		return NULL;
	}

	mm_copy(st_data_get(result), ((uchr_t *)&type), 1);
	mm_copy(st_data_get(result) + 1, ((uchr_t *)&big_endian_size) + 1, 3);

	if (st_valid_tracked(st_opt_get(result))){
		st_length_set(result, 4);
	}

	return result;
}
