#ifndef	_PLAYSTREAM_H_
#define	_PLAYSTREAM_H_

#ifndef __GRAPHICS_H
#include "Graphics.h"
#endif

#ifndef _TYPES_H
#include "Types.h"
#endif

#ifndef	_PREPARESTREAM_H_
#include "PrepareStream.h"
#endif

#include "DataAcq.h"
#include "SAudioSubscriber.h"
#include "CPakSubscriber.h"
#include "ControlSubscriber.h"
#include "DataStreamDebug.h"


typedef long (*PlayCPakUserFn)( void *ctx, void *userContext );

/**************************************/
/* Internal player context descriptor */
/**************************************/
typedef struct Player {

	PlayCPakUserFn		userFn;				/* user callback function pointer */
	void				*userContext;		/* for use by user callback function */

	DSHeaderChunk		hdr;				/* Copy of stream header from stream file */

	DSDataBufPtr		bufferList;			/* ptr to linked list of buffers used by streamer */
	AcqContextPtr		acqContext;			/* ptr to data acquisition thread's context */
	DSStreamCBPtr		streamCBPtr;		/* ptr to stream thread's context */

	ScreenContext		*screenContextPtr;	/* for drawing to the screen */
	Item				VBLIOReq;			/* ioreq for calling WaitVBL() */

	Item				messagePort;		/* port for receiving end of stream message */
	Item				messageItem;		/* msg item for sending streamer requests */
	Item				endOfStreamMessageItem; /* msg item that is replied to as end of stream */

	CtrlContextPtr		controlContextPtr;	/* Control subscriber context ptr */

	SAudioContextPtr	audioContextPtr;	/* Audio subscriber context ptr */

	CPakContextPtr		cpakContextPtr;		/* Cinepak subscriber context ptr */
	CPakRecPtr			cpakChannelPtr;		/* Cinepak subscriber channel ptr */

	} Player, *PlayerPtr;


/*****************************/
/* Public routine prototypes */
/*****************************/

int32	PlayCPakStream( ScreenContext *screenContextPtr, char* streamFileName, 
							PlayCPakUserFn userFn, void *userContext );
void	DismantlePlayer( PlayerPtr ctx );

#endif	/* _PLAYSTREAM_H_ */
